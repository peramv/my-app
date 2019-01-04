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
// ^FILE   : AgentBankInstructionsListRepository.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 02/25/2011
//
// ^CLASS    : AgentBankInstructionsListRepository
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "Agentbankinstructionslistrepository.hpp"
#include "RegAgentBankInstructionsList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("AgentBankInstructionsListRepository");
}

extern BF_OBJ_TYPE OBJ_TYPE_REG_AGENT_BANKLIST;	

//******************************************************************************
AgentBankInstructionsListRepository::AgentBankInstructionsListRepository(BFAbstractCBO &parent)
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
AgentBankInstructionsListRepository::~AgentBankInstructionsListRepository()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

/***********************************************************************************
 Input :BFDataGroupID,Track,pageName
 Output:None
 Return:SEVERITY
 Functionality:returns the severity while initalizing the AgentBankInst repository.
***********************************************************************************/
SEVERITY AgentBankInstructionsListRepository::init(const BFDataGroupId &idDataGroup /*= BF::HOST*/,
                                                   const DString& dstrTrack /*= I_("N")*/, 
                                                   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));  
   return GETCURRENTHIGHESTSEVERITY();
}

/***********************************************************************************
 Input :RegAgentCode,ref to the BFDataGroupID,Track,pageName
 Output:RegAgentBankInstructionList
 Return:SEVERITY
 Functionality:Creates the list of registartion agent related bank instructions and store it in the map as
 a repository by making a call to the RegAgentBankInstList init function whcih makes view call to Back end.
***********************************************************************************/

SEVERITY AgentBankInstructionsListRepository::getRegAgentBankInstructionsList(const DString	&dstrRegAgent, 
                                                RegAgentBankInstructionsList *&pRegAgentBankInstructionsList, 
                                                const BFDataGroupId &idDataGroup, 
                                                const DString	&dstrTrack , 
                                                const DString	&dstrPageName )
{

MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRegAgentBankInstructionsList"));
  
DString dstrKey;

buildKeyRegAgent(dstrRegAgent,dstrKey);

pRegAgentBankInstructionsList = dynamic_cast<RegAgentBankInstructionsList*>(getObject(dstrKey, idDataGroup));
	if (!pRegAgentBankInstructionsList)
	{
		pRegAgentBankInstructionsList = new RegAgentBankInstructionsList(*this);
		if(pRegAgentBankInstructionsList->init(dstrRegAgent,idDataGroup)<=WARNING)
		{
               setObject ( pRegAgentBankInstructionsList, 
                     dstrKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup, 
                      OBJ_TYPE_REG_AGENT_BANKLIST);
		}
		 else
			{
				delete pRegAgentBankInstructionsList;
				pRegAgentBankInstructionsList = NULL;
			}

   }
   return GETCURRENTHIGHESTSEVERITY();
}
/***********************************************************************************
 Input :RegAgentCode"
 Output:dstrKey
 Return:Void
 Functionality:Creates the  registartion agent key to be added as key in the repository
 to search once the lsit is created.
***********************************************************************************/

//******************************************************************************
void AgentBankInstructionsListRepository::buildKeyRegAgent( const DString& dstrRegAgentCode, 
                   					    DString& dstrKey )
{
   dstrKey = I_("RegAgent:")+ dstrRegAgentCode;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AgentBankInstructionsListRepository.cpp-arc  $
// 
//    Rev 1.1   Apr 03 2012 22:04:08   wp040039
// PETP0187485-Registartion Agent  Banking
// Implemented the code review comments.
// 
//    Rev 1.0   Apr 03 2012 21:29:56   wp040039
// Initial revision.
// 
//   
 */