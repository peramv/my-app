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
// ^FILE   : DirectTradingBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : DirectTradingBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "directtradingbankinstructionslist.hpp"
#include "bankinstructions4shlist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_ ("DirectTradingBankInstructionsList");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING;
}  


//******************************************************************************
DirectTradingBankInstructionsList::DirectTradingBankInstructionsList (BFAbstractCBO &parent)
: BankInstructions4ShList (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
DirectTradingBankInstructionsList::~DirectTradingBankInstructionsList ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY DirectTradingBankInstructionsList::initNew (const DString &dstrShrNum, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
   
   BankInstructions4ShList::initNew (dstrShrNum, BANKTYPE::DIRECT_TRADING,
      idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DirectTradingBankInstructionsList::init (const DString &dstrShrNum, 
   const DString &dstrTrack /*= I_("N")*/, 
   const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
  
   BankInstructions4ShList::init (dstrShrNum, BANKTYPE::DIRECT_TRADING);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DirectTradingBankInstructionsList.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:30:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Nov 10 2003 14:52:26   popescu
// Revised the names of the suppporting objects based on Desktop's naming standards
// 
//    Rev 1.2   Oct 19 2003 16:44:16   popescu
// CIBC, PET809, FN 13 banking work
// 
//    Rev 1.1   Oct 06 2003 12:47:26   popescu
// Removed un-wanted revision control comments
// 
//    Rev 1.0   Oct 06 2003 12:45:30   popescu
// Initial revision.
// 
 */