
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
// ^FILE : RegAgentBankInstructionsList.cpp
// ^AUTHOR :Robbins Kuriakose 
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************



#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include "RegAgentBankInstructionsList.hpp"
#include "Agentbankinstructionslistrepository.hpp"

namespace
{
   const I_CHAR * CLASSNAME = I_("RegAgentBankInstructionsList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId RegAgent;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,	  Group Flags
   { ifds::RegAgent, BFCBO::NONE, 0 }, 
};

namespace BANKENTITY
{
  extern I_CHAR * const  REG_AGENT;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const REG_AGENT;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
RegAgentBankInstructionsList::RegAgentBankInstructionsList(BFAbstractCBO &parent)
: BankInstructionsList(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList();
//the parent of this list should always be a RegAgentInstructionsListRepository object
   assert(dynamic_cast<AgentBankInstructionsListRepository*>(&parent));
}


//******************************************************************************
RegAgentBankInstructionsList::~RegAgentBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************

SEVERITY RegAgentBankInstructionsList::init( const DString &regAgent, 
                                                const BFDataGroupId &idDataGroup,
                                                const DString& dstrTrack /*= I_("N")*/, 
                                                const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
  
   BFData requestData (ifds::DSTC0052_REQ);

   requestData.setElementValue (ifds::BankingEntity, BANKENTITY::REG_AGENT);
   requestData.setElementValue (ifds::RegAgent, regAgent);
   setFieldNoValidate (ifds::RegAgent, regAgent, idDataGroup, false, true, true);
   BankInstructionsList::init (requestData, BANKTYPE::REG_AGENT, dstrTrack, dstrPageName);
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RegAgentBankInstructionsList.cpp-arc  $
// 
//    Rev 1.2   Apr 09 2012 13:24:34   wp040133
// P0187485
// Reg Agent banking setup ESS
// Adding the Include file names correctly to rectify the build errors
// 
//    Rev 1.1   Apr 03 2012 21:48:34   wp040039
// PETP0187485-Registartion Agent  Banking
// implementing review comments.
// 
//    Rev 1.0   Apr 03 2012 21:32:32   wp040039
// Initial revision.
// 

