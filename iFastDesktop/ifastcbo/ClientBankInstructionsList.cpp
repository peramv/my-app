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
// ^FILE   : ClientBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ^CLASS    : ClientBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include "clientbankinstructions.hpp"
#include "clientbankinstructionslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("ClientBankInstructionsList");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const CLIENT;
}

namespace BANKENTITY
{
   extern I_CHAR * const CLIENT;
}

//******************************************************************************
ClientBankInstructionsList::ClientBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsList(parent),
_parentCBO (NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
ClientBankInstructionsList::~ClientBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY ClientBankInstructionsList::init ( const BFDataGroupId& idDataGroup, 
                                            const DString& dstrTrack /*= I_("N")*/, 
                                            const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
  
   BFData requestData (ifds::DSTC0052_REQ);

   requestData.setElementValue (ifds::BankingEntity, BANKENTITY::CLIENT);
   BankInstructionsList::init (requestData, BANKTYPE::CLIENT, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline void ClientBankInstructionsList::
   setPayInstructionsAsParentCBO (BFAbstractCBO *pParentCBO)
{
   _parentCBO = pParentCBO;
}

//******************************************************************************
inline BFAbstractCBO * ClientBankInstructionsList::
   getPayInstructionsParentCBO  ()
{
   return _parentCBO;
}

//********************************************************************************
SEVERITY ClientBankInstructionsList::doCreateNewObject ( BFCBO*& pBase, DString &strKey, 
                                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   ClientBankInstructions *pClientBankInstructions = 
      new ClientBankInstructions (*this, BANKTYPE::CLIENT);

   pClientBankInstructions->initNew (idDataGroup);
   pBase = pClientBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ClientBankInstructionsList.cpp-arc  $
// 
//    Rev 1.3   Sep 12 2006 10:52:08   popescu
// STP - PET 2192/11
// 
//    Rev 1.2   Sep 10 2006 17:58:40   popescu
// STP 2192/12
// 
//    Rev 1.1   Nov 14 2004 14:29:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   May 31 2003 12:00:48   popescu
// Initial revision.
 */