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
// ^FILE   : SystematicBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May 2003
//
// ^CLASS    : SystematicBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include "SystematicBankInstructions.hpp"
#include "SystematicBankInstructionsList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("SystematicBankInstructionsList");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SYSTEMATIC;
}

//******************************************************************************
SystematicBankInstructionsList::SystematicBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsExList(parent, BANKTYPE::SYSTEMATIC, 
   ifds::DSTC0006_VW, ifds::DSTC0006_VWRepeat_Record)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
SystematicBankInstructionsList::~SystematicBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY SystematicBankInstructionsList::doCreateNewObject(BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   SystematicBankInstructions *pSystematicBankInstructions = 
      new SystematicBankInstructions(*this);

   pSystematicBankInstructions->initNew(idDataGroup);
   pBase = pSystematicBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SystematicBankInstructionsList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   SystematicBankInstructions *pSystematicBankInstructions = 
      new SystematicBankInstructions(*this);

   //this is Systematic's repeat view data
   pSystematicBankInstructions->init(data, BF::HOST);
   pObjOut = pSystematicBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SystematicBankInstructionsList.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:56:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Oct 04 2003 16:01:36   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.1   Jun 03 2003 20:59:30   popescu
// Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
// 
//    Rev 1.0   Jun 01 2003 17:09:40   popescu
// Initial revision.
// 
//    Rev 1.0   May 31 2003 12:00:58   popescu
// Initial revision.
 */