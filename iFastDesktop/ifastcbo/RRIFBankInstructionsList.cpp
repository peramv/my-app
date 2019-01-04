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
// ^FILE   : RRIFBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : May 2003
//
// ^CLASS    : RRIFBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0067_vw.hpp>
#include "RRIFBankInstructions.hpp"
#include "RRIFBankInstructionsList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("RRIFBankInstructionsList");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const RRIF;
}

//******************************************************************************
RRIFBankInstructionsList::RRIFBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsExList(parent, 
   BANKTYPE::RRIF, ifds::DSTC0067_VW, ifds::DSTC0067_VWRepeat_Record)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
RRIFBankInstructionsList::~RRIFBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY RRIFBankInstructionsList::doCreateNewObject(BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   RRIFBankInstructions *pRRIFBankInstructions = 
      new RRIFBankInstructions(*this);

   pRRIFBankInstructions->initNew(idDataGroup);
   pBase = pRRIFBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RRIFBankInstructionsList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   RRIFBankInstructions *pRRIFBankInstructions = 
      new RRIFBankInstructions(*this);

   //this is RRIF's repeat view data
   pRRIFBankInstructions->init(data, BF::HOST);
   pObjOut = pRRIFBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFBankInstructionsList.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:53:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Oct 04 2003 16:00:54   popescu
// CIBC PET 809, FN 13;
// also cleaned-up BankSearch and BankList objects,
// replaced with FinancialInstitutionList
// 
//    Rev 1.2   Jun 03 2003 20:59:24   popescu
// Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
// 
//    Rev 1.1   Jun 01 2003 17:07:58   popescu
// Systematic & Distribution banking work
// 
//    Rev 1.0   May 31 2003 12:00:58   popescu
// Initial revision.
 */