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
// ^FILE   : DistributionBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May, 2003
//
// ^CLASS    : DistributionBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0016_vw.hpp>
#include "DistributionBankInstructions.hpp"
#include "DistributionBankInstructionsList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("DistributionBankInstructionsList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
}

//******************************************************************************
DistributionBankInstructionsList::DistributionBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsExList(parent, BANKTYPE::DISTRIBUTION, 
   ifds::DSTC0016_VW, ifds::DSTC0016_VWRepeat_Record)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
DistributionBankInstructionsList::~DistributionBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY DistributionBankInstructionsList::doCreateNewObject(BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   DistributionBankInstructions *pDistributionBankInstructions = 
      new DistributionBankInstructions(*this);

   pDistributionBankInstructions->initNew(idDataGroup);
   pBase = pDistributionBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DistributionBankInstructionsList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   DistributionBankInstructions *pDistributionBankInstructions = 
      new DistributionBankInstructions(*this);

   //this is Distribution's repeat view data
   pDistributionBankInstructions->init(data, BF::HOST);
   pObjOut = pDistributionBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DistributionBankInstructionsList.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:30:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Oct 04 2003 15:58:52   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.1   Jun 03 2003 20:58:44   popescu
// Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
// 
//    Rev 1.0   Jun 01 2003 17:09:36   popescu
// Initial revision.
// 
//    Rev 1.0   May 31 2003 12:00:58   popescu
// Initial revision.
 */