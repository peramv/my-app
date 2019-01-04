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
// ^FILE   : DistributorBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/2003
//
// ^CLASS    : DistributorBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include "distributorbankinstructionslist.hpp"
#include "distributorbankinstructions.hpp"
#include "paymentinstructions.hpp"
#include "distributorrepository.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("DistributorBankInstructionsList");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,	  Group Flags
   {ifds::BrokerCode, BFCBO::NONE, 0}, 
   {ifds::BranchCode, BFCBO::NONE, 0}, 
   {ifds::SlsrepCode, BFCBO::NONE, 0}, 
};

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
	extern CLASS_IMPORT I_CHAR * const CLIENT;
}

namespace BANKENTITY
{
   extern I_CHAR * const BROKER;
   extern I_CHAR * const BRANCH;
   extern I_CHAR * const SALESREP;
	extern I_CHAR * const CLIENT;
}

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
DistributorBankInstructionsList::DistributorBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsList(parent),
_bankType(NULL_STRING),
_parentCBO (NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL);
   setObjectAsList();
//the parent of this list should always be a DistributorRepository object
   assert(dynamic_cast<DistributorRepository*>(&parent));
}

//******************************************************************************
DistributorBankInstructionsList::~DistributorBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
inline void DistributorBankInstructionsList::
   setPayInstructionsAsParentCBO (BFAbstractCBO *pParentCBO)
{
   _parentCBO = pParentCBO;
}

//******************************************************************************
inline BFAbstractCBO * DistributorBankInstructionsList::
   getPayInstructionsParentCBO  ()
{
   return _parentCBO;
}

//******************************************************************************
SEVERITY DistributorBankInstructionsList::init ( const DString& dstrBrokerCode, 
                                                 const DString& dstrBranchCode, 
	                                              const DString& dstrSlsrepCode,
                                                 const BFDataGroupId &idDataGroup,
                                                 const DString& dstrTrack /*= I_("N")*/, 
                                                 const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
  
   DString bankingEntity;
   BFData requestData (ifds::DSTC0052_REQ);

   if (!dstrSlsrepCode.empty())
   {
      bankingEntity = BANKENTITY::SALESREP;
      _bankType = BANKTYPE::SALESREP;
   }
   else if (!dstrBranchCode.empty())
   {
      bankingEntity = BANKENTITY::BRANCH;
      _bankType = BANKTYPE::BRANCH;
   }
   else if (!dstrBrokerCode.empty())
   {
      bankingEntity = BANKENTITY::BROKER;
      _bankType = BANKTYPE::BROKER;
   }

   requestData.setElementValue (ifds::BankingEntity, bankingEntity);
   requestData.setElementValue (ifds::BrokerCode, dstrBrokerCode);
   requestData.setElementValue (ifds::BranchCode, dstrBranchCode);
   requestData.setElementValue (ifds::SlsrepCode, dstrSlsrepCode);
   setFieldNoValidate (ifds::BrokerCode, dstrBrokerCode, BF::HOST, false, true, true);
   setFieldNoValidate (ifds::BranchCode, dstrBranchCode, BF::HOST, false, true, true);
   setFieldNoValidate (ifds::SlsrepCode, dstrSlsrepCode, BF::HOST, false, true, true);
   BankInstructionsList::init (requestData, _bankType, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY DistributorBankInstructionsList::doCreateNewObject (BFCBO*& pBase, DString& strKey, 
                                                             const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   DistributorBankInstructions *pDistributorBankInstructions = 
      new DistributorBankInstructions (*this, _bankType);

   pDistributorBankInstructions->initNew (idDataGroup);
   pBase = pDistributorBankInstructions;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DistributorBankInstructionsList.cpp-arc  $
// 
//    Rev 1.6   Sep 10 2006 17:58:58   popescu
// STP 2192/12
// 
//    Rev 1.5   Jul 31 2006 15:34:22   ZHANGCEL
// PET2192 FN11 -- MgmtCo Banking related changes
// 
//    Rev 1.4   Jul 27 2006 17:58:54   ZHANGCEL
// PET2192 FN11 - Commission Payments to MgmtCo related changes
// 
//    Rev 1.3   Nov 14 2004 14:30:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Aug 17 2003 16:16:46   popescu
// Use DistributorBankInstructions objects as children objects 
// 
//    Rev 1.1   Jul 30 2003 11:35:04   popescu
// Correspondent banking is enabled for Distribution banking, AcctUsage EFT, and moved some acct usage codes under the namespace AcctUseCode
// 
//    Rev 1.0   May 31 2003 12:00:38   popescu
// Initial revision.
 */