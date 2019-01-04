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
// ^FILE   : FundBankInstructionsListRepository.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ^CLASS    : FundBankInstructionsListRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundbankinstructionslistrepository.hpp"

#include "fundbankinstructionslist.hpp"
#include "fundgroupbankinstructionslist.hpp"
#include "fundsponsorbankinstructionslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("FundBankInstructionsListRepository");
}

extern BF_OBJ_TYPE OBJ_TYPE_FUND_BANK_LIST;

//******************************************************************************
FundBankInstructionsListRepository::FundBankInstructionsListRepository(BFAbstractCBO &parent)
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
FundBankInstructionsListRepository::~FundBankInstructionsListRepository()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY FundBankInstructionsListRepository::init( const BFDataGroupId &idDataGroup /*= BF::HOST*/,
                                                   const DString& dstrTrack /*= I_("N")*/, 
                                                   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));  
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundBankInstructionsListRepository::
         getFundBankInstructionsList ( const DString& dstrFundCode, 
                                       FundBankInstructionsList *&pFundBankInstructionsList, 
                                       const BFDataGroupId &idDataGroup, 
                                       const DString& dstrTrack /*= I_("N")*/, 
                                       const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundBankInstructionsList"));
  
   DString dstrKey;

   buildKey (dstrFundCode, dstrKey);   
   pFundBankInstructionsList = dynamic_cast <FundBankInstructionsList*> (getObject(dstrKey, idDataGroup));
   if (!pFundBankInstructionsList)
   {
      pFundBankInstructionsList = new FundBankInstructionsList(*this);
      if (pFundBankInstructionsList->init (dstrFundCode, idDataGroup) <= WARNING)
      {
         setObject( pFundBankInstructionsList, 
                    dstrKey, 
                    OBJ_ACTIVITY_NONE, 
                    idDataGroup, 
                    OBJ_TYPE_FUND_BANK_LIST);
      }
      else
      {
         delete pFundBankInstructionsList;
         pFundBankInstructionsList = NULL;
      }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundBankInstructionsListRepository::
         getFundBankInstructionsList( const DString& dstrFundCode, 
                                      const DString& dstrClassCode, 
                                      FundBankInstructionsList *&pFundBankInstructionsList, 
                                      const BFDataGroupId &idDataGroup, 
                                      const DString& dstrTrack /*= I_("N")*/, 
                                      const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundBankInstructionsList"));
  
   DString dstrKey;

   buildKey (dstrFundCode, dstrClassCode, dstrKey);   
   pFundBankInstructionsList = dynamic_cast<FundBankInstructionsList*>(getObject(dstrKey, idDataGroup));
   if (!pFundBankInstructionsList)
   {
      pFundBankInstructionsList = new FundBankInstructionsList(*this);
      if (pFundBankInstructionsList->init (dstrFundCode, dstrClassCode, idDataGroup) <= WARNING)
      {
         setObject ( pFundBankInstructionsList, 
                     dstrKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup, 
                     OBJ_TYPE_FUND_BANK_LIST);
      }
      else
      {
         delete pFundBankInstructionsList;
         pFundBankInstructionsList = NULL;
      }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundBankInstructionsListRepository::
         getFundGroupBankInstructionsList( const DString& fundGroup,
                                           FundGroupBankInstructionsList *&pFundGroupBankInstructionsList, 
                                           const BFDataGroupId &idDataGroup, 
                                           const DString& dstrTrack /*= I_("N")*/, 
                                           const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundGroupBankInstructionsList"));
  
   DString dstrKey;

   dstrKey = I_("FundGroup:") + fundGroup;
   pFundGroupBankInstructionsList = dynamic_cast<FundGroupBankInstructionsList*>(getObject(dstrKey, idDataGroup));
   if (!pFundGroupBankInstructionsList)
   {
      pFundGroupBankInstructionsList = new FundGroupBankInstructionsList(*this);
      if (pFundGroupBankInstructionsList->init (fundGroup, idDataGroup) <= WARNING)
      {
         setObject ( pFundGroupBankInstructionsList, 
                     dstrKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup, 
                     OBJ_TYPE_FUND_BANK_LIST);
      }
      else
      {
         delete pFundGroupBankInstructionsList;
         pFundGroupBankInstructionsList = NULL;
      }

   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY FundBankInstructionsListRepository::
         getFundSponsorBankInstructionsList( const DString &fundSponsor,
                                             FundSponsorBankInstructionsList *&pFundSponsorBankInstructionsList, 
                                             const BFDataGroupId &idDataGroup, 
                                             const DString &dstrTrack /*= I_("N")*/, 
                                             const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundSponsorBankInstructionsList"));
  
   DString dstrKey;

   dstrKey = I_("FundSponsor:") + fundSponsor;
   pFundSponsorBankInstructionsList = dynamic_cast<FundSponsorBankInstructionsList*>(getObject(dstrKey, idDataGroup));
   if (!pFundSponsorBankInstructionsList)
   {
      pFundSponsorBankInstructionsList = new FundSponsorBankInstructionsList(*this);
      if (pFundSponsorBankInstructionsList->init (fundSponsor, idDataGroup) <= WARNING)
      {
         setObject ( pFundSponsorBankInstructionsList, 
                     dstrKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup, 
                     OBJ_TYPE_FUND_BANK_LIST);
      }
      else
      {
         delete pFundSponsorBankInstructionsList;
         pFundSponsorBankInstructionsList = NULL;
      }

   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FundBankInstructionsListRepository::buildKey ( const DString& dstrFundCode, 
                                                    DString& dstrKey)
{
   dstrKey = I_("FundCode:") + dstrFundCode;
}

//******************************************************************************
void FundBankInstructionsListRepository::buildKey ( const DString& dstrFundCode, 
                                                    const DString& dstrClassCode, 
                                                    DString& dstrKey)
{
   dstrKey = I_("FundCode:") + dstrFundCode;
   dstrKey = I_("ClassCode:") + dstrClassCode;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBankInstructionsListRepository.cpp-arc  $
// 
//    Rev 1.4   Oct 18 2006 15:53:48   popescu
// PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
// 
//    Rev 1.3   Nov 14 2004 14:41:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Sep 21 2004 13:30:56   HERNANDO
// PET1094 FN06 - Absatzmeldung Files enhancement.  Added getFundGroupBankInstructionsList.
// 
//    Rev 1.1   Jun 09 2003 17:40:04   popescu
// Added support for fund and class search, still stopped at the Gui level, because it shouldn't be functional yet; do not know the id for the bank entity when seraching for bank using fund and class
// 
//    Rev 1.0   May 31 2003 12:00:52   popescu
// Initial revision.
 */