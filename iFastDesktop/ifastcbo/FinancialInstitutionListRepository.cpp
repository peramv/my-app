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
// ^FILE   : FinancialInstitutionListRepository.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : FinancialInstitutionListRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "financialinstitutionlist.hpp"
#include "financialinstitutiontransitlist.hpp"
#include "financialinstitutionlistrepository.hpp"

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME = I_("FinancialInstitutionListRepository");
   const I_CHAR * FI_KEY = I_("FinancialInstitutionList");
   const I_CHAR * FIT_KEY = I_("FinancialInstitutionTransitsList");
}

extern BF_OBJ_TYPE OBJ_TYPE_FINANCIAL_INSTITUTION_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_FINANCIAL_INSTITUTION_TRANSIT_LIST;
//******************************************************************************
FinancialInstitutionListRepository::FinancialInstitutionListRepository (BFAbstractCBO &parent)
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}

//******************************************************************************
FinancialInstitutionListRepository::~FinancialInstitutionListRepository()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY FinancialInstitutionListRepository::init(
   const BFDataGroupId &idDataGroup /*= BF::HOST*/,
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));  
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionListRepository::getFinancialInstitutionList(
   FinancialInstitutionList *&pFinancialInstitutionList, 
   const BFDataGroupId &idDataGroup, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_("getFinancialInstitutionList"));
  
   DString dstrKey;

   buildFIKey (dstrKey);
   pFinancialInstitutionList = dynamic_cast<FinancialInstitutionList*>(
      getObject(dstrKey, idDataGroup));
   if (!pFinancialInstitutionList)
   {
      pFinancialInstitutionList = 
         new FinancialInstitutionList (*this);
      if (pFinancialInstitutionList->initAll (dstrTrack, dstrPageName) <= WARNING)
      {
         setObject (pFinancialInstitutionList, dstrKey, 
            OBJ_ACTIVITY_NONE, idDataGroup, OBJ_TYPE_FINANCIAL_INSTITUTION_LIST);
      }
      else
      {
         delete pFinancialInstitutionList;
         pFinancialInstitutionList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionListRepository::getFinancialInstitutionList(
   const DString &dstrName,
   FinancialInstitutionList *&pFinancialInstitutionList, 
   const BFDataGroupId &idDataGroup, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFinancialInstitutionList"));
  
   DString dstrKey;

   buildFIKey (dstrKey);
   pFinancialInstitutionList = dynamic_cast<FinancialInstitutionList*>(
      getObject(dstrKey, idDataGroup));
   if (!pFinancialInstitutionList)
   {
      pFinancialInstitutionList = 
         new FinancialInstitutionList (*this);
      if (pFinancialInstitutionList->initAllForName (dstrName, 
         dstrTrack, dstrPageName) <= WARNING)
      {
         setObject (pFinancialInstitutionList, dstrKey, 
            OBJ_ACTIVITY_NONE, idDataGroup, OBJ_TYPE_FINANCIAL_INSTITUTION_LIST);
      }
      else
      {
         delete pFinancialInstitutionList;
         pFinancialInstitutionList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionListRepository::getFinancialInstitutionList(
   const DString &dstrCategory,
   const DString &dstrType,
   const DString &dstrCode,
   FinancialInstitutionList *&pFinancialInstitutionList, 
   const BFDataGroupId &idDataGroup, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFinancialInstitutionList"));
  
   DString dstrKey;

   buildFIKey (dstrKey);
   pFinancialInstitutionList = dynamic_cast<FinancialInstitutionList*>(
      getObject (dstrKey, idDataGroup));
   if (!pFinancialInstitutionList)
   {
      pFinancialInstitutionList = 
         new FinancialInstitutionList (*this);
      if (pFinancialInstitutionList->init (dstrCategory, 
         dstrType, dstrCode, dstrTrack, dstrPageName) <= WARNING)
      {
         setObject (pFinancialInstitutionList, dstrKey, 
            OBJ_ACTIVITY_NONE, idDataGroup, OBJ_TYPE_FINANCIAL_INSTITUTION_LIST);
      }
      else
      {
         delete pFinancialInstitutionList;
         pFinancialInstitutionList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionListRepository::getTransits (
   FinancialInstitutionTransitList *&pFinancialInstitutionTransitList, 
   const BFDataGroupId &idDataGroup, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_("getTransits"));
   DString strKey;

   buildFITKey (strKey);
   pFinancialInstitutionTransitList = dynamic_cast<FinancialInstitutionTransitList*>(
      getObject(strKey, idDataGroup));

   if (!pFinancialInstitutionTransitList)
   {
      pFinancialInstitutionTransitList = 
         new FinancialInstitutionTransitList (*this);
      if (pFinancialInstitutionTransitList->initAll (dstrTrack, 
         dstrPageName) <= WARNING)
      {
         setObject (pFinancialInstitutionTransitList, strKey, 
            OBJ_ACTIVITY_NONE, idDataGroup, 
            OBJ_TYPE_FINANCIAL_INSTITUTION_TRANSIT_LIST);
      }
      else
      {
         delete pFinancialInstitutionTransitList;
         pFinancialInstitutionTransitList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionListRepository::getTransits (
   const DString &dstrName,
   FinancialInstitutionTransitList *&pFinancialInstitutionTransitList, 
   const BFDataGroupId &idDataGroup, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransits"));
   DString strKey;

   buildFITKey (strKey);
   pFinancialInstitutionTransitList = dynamic_cast<FinancialInstitutionTransitList*>(
      getObject(strKey, idDataGroup));

   if (!pFinancialInstitutionTransitList)
   {
      pFinancialInstitutionTransitList = 
         new FinancialInstitutionTransitList (*this);
      if (pFinancialInstitutionTransitList->initAllForName (dstrName, dstrTrack, 
         dstrPageName) <= WARNING)
      {
         setObject (pFinancialInstitutionTransitList, strKey, 
            OBJ_ACTIVITY_NONE, idDataGroup, 
            OBJ_TYPE_FINANCIAL_INSTITUTION_TRANSIT_LIST);
      }
      else
      {
         delete pFinancialInstitutionTransitList;
         pFinancialInstitutionTransitList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FinancialInstitutionListRepository::getTransits (
   const DString &category,
   const DString &type, 
   const DString &code,
   FinancialInstitutionTransitList *&pFinancialInstitutionTransitList,
   const BFDataGroupId &idDataGroup,
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransits"));

   DString strKey;

   buildFITKey (strKey, category, type, code);
   pFinancialInstitutionTransitList = dynamic_cast<FinancialInstitutionTransitList*>(
      getObject(strKey, idDataGroup));

   if (!pFinancialInstitutionTransitList)
   {
      pFinancialInstitutionTransitList = 
         new FinancialInstitutionTransitList (*this);
      if (pFinancialInstitutionTransitList->init (category, type, 
         code, NULL_STRING) <= WARNING)
      {
         setObject (pFinancialInstitutionTransitList, strKey, 
            OBJ_ACTIVITY_NONE, idDataGroup, 
            OBJ_TYPE_FINANCIAL_INSTITUTION_TRANSIT_LIST);
      }
      else
      {
         delete pFinancialInstitutionTransitList;
         pFinancialInstitutionTransitList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
void FinancialInstitutionListRepository::buildFIKey (DString &dstrKey)
{
   dstrKey = FI_KEY;
}

//******************************************************************************
void FinancialInstitutionListRepository::buildFITKey (DString &dstrKey)
{
   dstrKey = FIT_KEY;
}

//******************************************************************************
void FinancialInstitutionListRepository::buildFITKey (DString &dstrKey, 
   const DString &dstrCategory, const DString &dstrBankType, 
   const DString &dstrInstCode)
{
   DString category (dstrCategory);
   DString bankType (dstrBankType);
   DString instCode (dstrInstCode);

   dstrKey = 
      I_("Category=") + category.stripAll().upperCase() + 
      I_(";BankType=") + bankType.stripAll().upperCase() + 
      I_(";InstCode=") + instCode.stripAll().upperCase();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FinancialInstitutionListRepository.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:40:54   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Oct 27 2003 19:48:42   popescu
// CIBC PET809, FN 13, added Transit Search by name
// 
//    Rev 1.1   Oct 24 2003 17:19:40   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 04 2003 16:08:46   popescu
// Initial revision.
// 
 */