//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DailyTransactionsFeesRepository.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan, 2004
//
// ^CLASS    : DailyTransactionsFeesRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "dailytransactionsfeesrepository.hpp"
#include "dailytransactionsfeelist.hpp"

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME = I_("DailyTransactionsFeesRepository");
   const I_CHAR * DTF_KEY = I_("DailyTransactionsFeeList");
}

extern BF_OBJ_TYPE OBJ_TYPE_DAILY_TRANSACTIONS_FEE_LIST;
//******************************************************************************
DailyTransactionsFeesRepository::DailyTransactionsFeesRepository (BFAbstractCBO &parent)
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}

//******************************************************************************
DailyTransactionsFeesRepository::~DailyTransactionsFeesRepository()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY DailyTransactionsFeesRepository::init(
   const BFDataGroupId &idDataGroup /*= BF::HOST*/,
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));  
   return GETCURRENTHIGHESTSEVERITY();
}

//mainly used by the search by fund/class
//******************************************************************************
SEVERITY DailyTransactionsFeesRepository::getDailyTransactionsFeeList (
   const DString &recordType,
   const DString &feeCode,
   const DString &fundCode,
   const DString &classCode,
   DailyTransactionsFeeList *&pDailyTransactionsFeeList, 
   const BFDataGroupId &idDataGroup, 
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_("getDailyTransactionsFeeList"));
  
   DString dstrKey;

   buildDTFKey (dstrKey);
   pDailyTransactionsFeeList = dynamic_cast<DailyTransactionsFeeList*>(
      getObject (dstrKey, idDataGroup));
   if (!pDailyTransactionsFeeList)
   {
      pDailyTransactionsFeeList = 
         new DailyTransactionsFeeList (*this);
      if (pDailyTransactionsFeeList->init (
         recordType,
         feeCode,
         fundCode,
         classCode,
         NULL_STRING, //effective date
			NULL_STRING,  // stop date
			I_( "0" ),  // rec Id
         I_("N"), //duplicate check
         idDataGroup,
         dstrTrack, 
         dstrPageName) <= WARNING)
      {
         setObject (
            pDailyTransactionsFeeList, 
            dstrKey, 
            OBJ_ACTIVITY_NONE, 
            idDataGroup, 
            OBJ_TYPE_DAILY_TRANSACTIONS_FEE_LIST);
      }
      else
      {
         delete pDailyTransactionsFeeList;
         pDailyTransactionsFeeList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//mainly used by the search by effective date
//******************************************************************************
SEVERITY DailyTransactionsFeesRepository::getDailyTransactionsFeeList (
   const DString &recordType,
   const DString &feeCode,
   const DString &effectiveDate,
   DailyTransactionsFeeList *&pDailyTransactionsFeeList, 
   const BFDataGroupId &idDataGroup, 
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_("getDailyTransactionsFeeList"));
  
   DString dstrKey;

   buildDTFKey (dstrKey);
   pDailyTransactionsFeeList = dynamic_cast<DailyTransactionsFeeList*>(
      getObject (dstrKey, idDataGroup));
   if (!pDailyTransactionsFeeList)
   {
      pDailyTransactionsFeeList = 
         new DailyTransactionsFeeList (*this);
      if (pDailyTransactionsFeeList->init (
         recordType,
         feeCode,
         NULL_STRING, //fund code
         NULL_STRING, //class code
         effectiveDate, //effective date
			NULL_STRING,   // stop date
			I_( "0" ),   // recId
         I_("N"), //duplicate check
         idDataGroup,
         dstrTrack, 
         dstrPageName) <= WARNING)
      {
         setObject (
            pDailyTransactionsFeeList, 
            dstrKey, 
            OBJ_ACTIVITY_NONE, 
            idDataGroup, 
            OBJ_TYPE_DAILY_TRANSACTIONS_FEE_LIST);
      }
      else
      {
         delete pDailyTransactionsFeeList;
         pDailyTransactionsFeeList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void DailyTransactionsFeesRepository::buildDTFKey (DString &dstrKey)
{
   dstrKey = DTF_KEY;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DailyTransactionsFeesRepository.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:30:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Feb 25 2004 13:31:50   VADEANUM
// PET859 FN23 - ADL - Layout change for 284, modified signature of DailyTransactionsFees::init().
// 
//    Rev 1.1   Feb 12 2004 13:31:06   VADEANUM
// PET859 FN23 - ADL - modified signature of DailyTransactionsFees::init().
// 
//    Rev 1.0   Jan 28 2004 14:07:06   popescu
// Initial revision.
// 
//    Rev 1.2   Oct 27 2003 19:48:42   popescu
// 
 */